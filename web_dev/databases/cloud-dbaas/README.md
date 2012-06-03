web_dev > databases > cloud-dbaas
=================================

Database As a Service (DBaaS)

* [Amazon SimpleDB (AWS)](http://aws.amazon.com/simpledb/)
  * 1 GB / month
  * 25 machine hours / month

* [Salesforce database.com](http://database.com/)
  * 50,000 Transactions (API calls) / month
  * 100,000 records
  * *more...*

  * **Schema Builder**

  * [`gem 'databasedotcom'`](https://github.com/heroku/databasedotcom)


## database.com

#### Usage

1. Create account
2. Log in
3. Read docs, e.g. [REST API](http://www.salesforce.com/us/developer/docs/dbcom_api_rest/dbcom_api_rest.pdf)

  1. Log in
  2. Develop > Remote Access
  3. New
     * Application: `buildingup - dev`
     * Callback URL: `http://localhost:5000/`
     * Contact Email: `your_email@domain.ext`


     [Tutorial](http://www.salesforce.com/us/developer/docs/workbook_database/workbook_database.pdf)
     * Section: `Tutorial: Creating a Java Web Application to Access the Database`


#### Create Sandbox (Test Database)

1. Log in to your database.com
2. Data Management > Test Database > New Test Database


#### databasedotcom.yml
``` YAML
  client_id: 3MVG.....
  client_secret: 1323224123...
  username: mysalesforceusername@login.com
  password: passwordPlusSecToken
  host: login.salesforce.com <-- use test.salesforcecom if using a sandbox
  debugging: true
```


#### Security and the API

Password + Security Token
http://www.salesforce.com/us/developer/docs/api/Content/sforce_api_concepts_security.htm

** Get Security Token **
* `Reset Security Token` and then token will be emailed to you


#### Tutorials
http://fractastical.com/2011/11/21/my-first-ruby-on-rails-app-with-the-databasedotcom-gem/
