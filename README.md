## HELLO API
Welcome to my first API ~~attempt~~ in C.

# Workflow

- A POST request is made to the 42 api to obtain a token.  
- With the token in hands, a GET request is made asking for info about the username present in the uri.  
- If successfull, a parsing process takes place, obtaining a json ready to be delivered.  
- Finally, the json is returned and the api waits for other request.

**this api works with one request at a time**
**Only for 42 students**

## **Built with**
- Notion  
- Visual Studio Code  
- Pandoc  
- MongoDB Atlas  
- Mongoose  
- MJson  
- Github projects  
- Insomnia

## Dependencies
- gcc 
- make
- dumb-init
- libmongoc-1.0-0
- libmongoc-dev
- libmbedtls-dev  
**In order to use the api you need to have 3 environment variables:  
C_ID(Client Id),  
C_SECRET(Client secret) and   
MONGO_CLIENT(Your mongo atlas connection string).**  

## **Compile and run**
With everything installed, you can just compile by using make.  

## **Using Docker**
You can download my docker image [here](https://hub.docker.com/layers/rogeriorslf/helloapi/v1/images/sha256-d646a8a05048dedd3498d2be64e7774c00f4fdd30e5ef33fff5479bdb240fabb?context=explore)  
To make it work you will have to use this command:  
*docker run --env-file {env_file PATH} -p 4242:4242 rogeriorslf/helloapi:v1*  
this env_file has to contain the environment variables

## **Endpoints**

**/docs**
 
Here you find how you my api works.     

**/api/v1/intra_login**
  
Using this endpoint you get some informations about the user(intra_login) defined in the uri.  
Here is an example showing what you get by using the endpoint /api/v1/rsiqueir :  
```json
{
  "login": "rsiqueir",
  "full_name": "Rogerio Siqueira Lima Filho",
  "trail": "Knowledge",
  "evaluation_points": 1,
  "eval_points_comment": "Fair enough",
  "global_average": 66,
  "retrys_average": 0.67,
  "stormtrooper?": "Yes"
}
```
