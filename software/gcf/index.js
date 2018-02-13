'use strict';

const functions = require('firebase-functions'); // Cloud Functions for Firebase library
const DialogflowApp = require('actions-on-google').DialogflowApp; // Google Assistant helper library
const http = require('http');
const host = 'api.worldweatheronline.com';
const wwoApiKey = '6468907fa0c44d05aa6160331180902';

exports.dialogflowFirebaseFulfillment = functions.https.onRequest((request, response) => {
  console.log('Dialogflow Request headers: ' + JSON.stringify(request.headers));
  console.log('Dialogflow Request body: ' + JSON.stringify(request.body));
  if (request.body.result) {
    processV1Request(request, response);
  } else {
    console.log('Invalid Request');
    return response.status(400).end('Invalid Webhook Request (expecting v1 or v2 webhook request)');
  }
});
/*
* Function to handle v1 webhook requests from Dialogflow
*/
function processV1Request (request, response) {
  let action = request.body.result.action; // https://dialogflow.com/docs/actions-and-parameters
  let parameters = request.body.result.parameters; // https://dialogflow.com/docs/actions-and-parameters
  let inputContexts = request.body.result.contexts; // https://dialogflow.com/docs/contexts
  let requestSource = (request.body.originalRequest) ? request.body.originalRequest.source : undefined;
  console.log(request.body);
  console.log(inputContexts);
  const googleAssistantRequest = 'google'; // Constant to identify Google Assistant requests
  const app = new DialogflowApp({request: request, response: response});
  // Create handlers for Dialogflow actions as well as a 'default' handler
  const actionHandlers = {
    // The default welcome intent has been matched, welcome the user (https://dialogflow.com/docs/events#default_welcome_intent)
    'input.welcome': () => {
      // Use the Actions on Google lib to respond to Google requests; for other requests use JSON
        if (requestSource === googleAssistantRequest) {
            const permissions = [
                app.SupportedPermissions.NAME,
                app.SupportedPermissions.DEVICE_PRECISE_LOCATION
            ];
            app.askForPermissions('Hello, I am Yogi, your personal health assistant. To begin', permissions);
      } else {
            sendResponse('Hello, I am Yogi, your personal health assistant'); // Send simple response to user
      }
    },
    // The default fallback intent has been matched, try to recover (https://dialogflow.com/docs/intents#fallback_intents)
    'input.unknown': () => {
      // Use the Actions on Google lib to respond to Google requests; for other requests use JSON
      if (requestSource === googleAssistantRequest) {
        sendGoogleResponse('I\'m having trouble, can you try that again?'); // Send simple response to user
      } else {
        sendResponse('I\'m having trouble, can you try that again?'); // Send simple response to user
      }
    },
    'user_info': () => {
        if (requestSource === googleAssistantRequest) {
          sendGoogleResponse('Thank you!'); // Send simple response to user
        } else {
          sendResponse('Thank you!'); // Send simple response to user
        }
    },
    'weather': () => {
        let hasWeatherContext = false;
        let weatherContextIndex = 0;
        for (var i = 0; i < inputContexts.length; i++) {
            if (inputContexts[i].name == "weather" && inputContexts[i].parameters.location) {
                hasWeatherContext = true;
                weatherContextIndex = i;
            }
        }
        let city = '';
        if (request.body.result.parameters.location){
            city = request.body.result.parameters.location.city || request.body.result.parameters.location.country;
        } else if (hasWeatherContext) {
            city = inputContexts[weatherContextIndex].parameters.location.city || inputContexts[weatherContextIndex].parameters.location.country;
        }
        else {
            city = [request.body.originalRequest.data.device.location.coordinates.latitude, request.body.originalRequest.data.device.location.coordinates.longitude].join(",");
        }
          // Get the date for the weather forecast (if present)
        let date = '';
        if (request.body.result.parameters.date) {
            date = request.body.result.parameters.date;
            console.log('Date: ' + date);
        } else if (hasWeatherContext){
            date = inputContexts[weatherContextIndex].date;
        } else {}
        // Call the weather API
        callWeatherApi(city, date).then((output) => {
            // Return the results of the weather API to Dialogflow
            response.setHeader('Content-Type', 'application/json');
            response.send(JSON.stringify({ 'speech': output, 'displayText': output }));
          }).catch((error) => {
            // If there is an error let the user know
            response.setHeader('Content-Type', 'application/json');
            response.send(JSON.stringify({ 'speech': error, 'displayText': error }));
          });
    },
    'weather.condition': () => {
        let hasWeatherContext = false;
        let weatherContextIndex = 0;
        for (var i = 0; i < inputContexts.length; i++) {
            if (inputContexts[i].name == "weather" && inputContexts[i].parameters.location) {
                hasWeatherContext = true;
                weatherContextIndex = i;
            }
        }
        let userCondition = '';
        if (request.body.result.parameters.condition){
            userCondition = request.body.result.parameters.condition;
        } else {
            userCondition = inputContexts[weatherContextIndex].parameters.condition;
        };
        let city = '';
        if (request.body.result.parameters.location){
            city = request.body.result.parameters.location.city || request.body.result.parameters.location.country;
        } else if (hasWeatherContext) {
            city = inputContexts[weatherContextIndex].parameters.location.city || inputContexts[weatherContextIndex].parameters.location.country;
        }
        else {
            city = [request.body.originalRequest.data.device.location.coordinates.latitude, request.body.originalRequest.data.device.location.coordinates.longitude].join(",");
        }
          // Get the date for the weather forecast (if present)
        let date = '';
        if (request.body.result.parameters.date) {
            date = request.body.result.parameters.date;
            console.log('Date: ' + date);
        } else {
            date = inputContexts[weatherContextIndex].parameters.date;
        }
        // Call the weather API
        callWeatherApiCondition(userCondition, city, date).then((output) => {
            // Return the results of the weather API to Dialogflow
            response.setHeader('Content-Type', 'application/json');
            response.send(JSON.stringify({ 'speech': output, 'displayText': output }));
          }).catch((error) => {
            // If there is an error let the user know
            response.setHeader('Content-Type', 'application/json');
            response.send(JSON.stringify({ 'speech': error, 'displayText': error }));
          });
    },
    // Default handler for unknown or undefined actions
    'default': () => {
        // Use the Actions on Google lib to respond to Google requests; for other requests use JSON
        if (requestSource === googleAssistantRequest) {
        let responseToUser = {
          //googleRichResponse: googleRichResponse, // Optional, uncomment to enable
          //googleOutputContexts: ['weather', 2, { ['city']: 'rome' }], // Optional, uncomment to enable
          speech: 'This message is from Dialogflow\'s Cloud Functions for Firebase editor!', // spoken response
          text: 'This is from Dialogflow\'s Cloud Functions for Firebase editor! :-)' // displayed response
        };
        sendGoogleResponse(responseToUser);
      } else {
        let responseToUser = {
          //data: richResponsesV1, // Optional, uncomment to enable
          //outputContexts: [{'name': 'weather', 'lifespan': 2, 'parameters': {'city': 'Rome'}}], // Optional, uncomment to enable
          speech: 'This message is from Dialogflow\'s Cloud Functions for Firebase editor!', // spoken response
          text: 'This is from Dialogflow\'s Cloud Functions for Firebase editor! :-)' // displayed response
        };
        sendResponse(responseToUser);
      }
    }
  };
  // If undefined or unknown action use the default handler
  if (!actionHandlers[action]) {
    action = 'default';
  }
  // Run the proper handler function to handle the request from Dialogflow
  actionHandlers[action]();
    // Function to send correctly formatted Google Assistant responses to Dialogflow which are then sent to the user
  function sendGoogleResponse (responseToUser) {
    if (typeof responseToUser === 'string') {
      app.ask(responseToUser); // Google Assistant response
    } else {
      // If speech or displayText is defined use it to respond
      let googleResponse = app.buildRichResponse().addSimpleResponse({
        speech: responseToUser.speech || responseToUser.displayText,
        displayText: responseToUser.displayText || responseToUser.speech
      });
      // Optional: Overwrite previous response with rich response
      if (responseToUser.googleRichResponse) {
        googleResponse = responseToUser.googleRichResponse;
      }
      // Optional: add contexts (https://dialogflow.com/docs/contexts)
      if (responseToUser.googleOutputContexts) {
        app.setContext(...responseToUser.googleOutputContexts);
      }
      console.log('Response to Dialogflow (AoG): ' + JSON.stringify(googleResponse));
      app.ask(googleResponse); // Send response to Dialogflow and Google Assistant
    }
  }
  // Function to send correctly formatted responses to Dialogflow which are then sent to the user
  function sendResponse (responseToUser) {
    // if the response is a string send it as a response to the user
    if (typeof responseToUser === 'string') {
      let responseJson = {};
      responseJson.speech = responseToUser; // spoken response
      responseJson.displayText = responseToUser; // displayed response
      response.json(responseJson); // Send response to Dialogflow
    } else {
      // If the response to the user includes rich responses or contexts send them to Dialogflow
      let responseJson = {};
      // If speech or displayText is defined, use it to respond (if one isn't defined use the other's value)
      responseJson.speech = responseToUser.speech || responseToUser.displayText;
      responseJson.displayText = responseToUser.displayText || responseToUser.speech;
      // Optional: add rich messages for integrations (https://dialogflow.com/docs/rich-messages)
      responseJson.data = responseToUser.data;
      // Optional: add contexts (https://dialogflow.com/docs/contexts)
      responseJson.contextOut = responseToUser.outputContexts;
      console.log('Response to Dialogflow: ' + JSON.stringify(responseJson));
      response.json(responseJson); // Send response to Dialogflow
    }
  }
}
function callWeatherApi (city, date) {
  return new Promise((resolve, reject) => {
    // Create the path for the HTTP request to get the weather
    let path = '/premium/v1/weather.ashx?format=json&num_of_days=1' +
      '&q=' + city + '&key=' + wwoApiKey + '&date=' + date + '&includelocation=yes';
    console.log('API Request: ' + host + path);
    // Make the HTTP request to get the weather
    http.get({host: host, path: path}, (res) => {
      let body = ''; // var to store the response chunks
      res.on('data', (d) => { body += d; }); // store each response chunk
      res.on('end', () => {
        // After all the data has been received parse the JSON for desired data
        let response = JSON.parse(body);
        let forecast = response['data']['weather'][0];
        let location = response['data']['nearest_area'][0]['region'][0];
        let conditions = response['data']['current_condition'][0];
        let currentConditions = conditions['weatherDesc'][0]['value'].toLowerCase();
        let now = new Date();
        let requested = new Date(forecast['date'].split("-"));
        let intro = (requested > now) ? "Forecasted conditions" : "Current conditions";
        // Create response
        let output = `${intro} in ${location['value']} are ${currentConditions} with a projected high of ${forecast['maxtempC']}°C and a low of ${forecast['mintempC']}°C.`;
        // Resolve the promise with the output text
        console.log(output);
        resolve(output);
      });
      res.on('error', (error) => {
        reject(error);
      });
    });
  });
}
function callWeatherApiCondition (userCondition, city, date) {
  return new Promise((resolve, reject) => {
    // Create the path for the HTTP request to get the weather
    let path = '/premium/v1/weather.ashx?format=json&num_of_days=1' +
      '&q=' + city + '&key=' + wwoApiKey + '&date=' + date + '&includelocation=yes';
    console.log('API Request: ' + host + path);
    // Make the HTTP request to get the weather
    http.get({host: host, path: path}, (res) => {
      let body = ''; // var to store the response chunks
      res.on('data', (d) => { body += d; }); // store each response chunk
      res.on('end', () => {
        // After all the data has been received parse the JSON for desired data
        let response = JSON.parse(body);
        let forecast = response['data']['weather'][0];
        let location = response['data']['nearest_area'][0]['region'][0];
        let conditions = response['data']['current_condition'][0];
        let currentConditions = conditions['weatherDesc'][0]['value'].toLowerCase();
        let now = new Date();
        let requested = new Date(forecast['date'].split("-"));
        let intro = (currentConditions.search(userCondition) > -1) ? "Yes" : "No";
        let grammar = (requested > now) ? "will be" : "is";
        // Create response
        let output = `${intro}, it ${grammar} ${currentConditions} in ${location['value']}.`;
        // Resolve the promise with the output text
        console.log(output);
        resolve(output);
      });
      res.on('error', (error) => {
        reject(error);
      });
    });
  });
}
// Construct rich response for Google Assistant (v1 requests only)
const app = new DialogflowApp();
const googleRichResponse = app.buildRichResponse()
  .addSimpleResponse('This is the first simple response for Google Assistant')
  .addSuggestions(
    ['Suggestion Chip', 'Another Suggestion Chip'])
    // Create a basic card and add it to the rich response
  .addBasicCard(app.buildBasicCard(`This is a basic card.  Text in a
 basic card can include "quotes" and most other unicode characters
 including emoji 📱.  Basic cards also support some markdown
 formatting like *emphasis* or _italics_, **strong** or __bold__,
 and ***bold itallic*** or ___strong emphasis___ as well as other things
 like line  \nbreaks`) // Note the two spaces before '\n' required for a
                        // line break to be rendered in the card
    .setSubtitle('This is a subtitle')
    .setTitle('Title: this is a title')
    .addButton('This is a button', 'https://assistant.google.com/')
    .setImage('https://developers.google.com/actions/images/badges/XPM_BADGING_GoogleAssistant_VER.png',
      'Image alternate text'))
  .addSimpleResponse({ speech: 'This is another simple response',
    displayText: 'This is the another simple response 💁' });