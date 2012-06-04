rails-docs
==========

## Rails Application Templates
* RailsApps [Website](http://railsapps.github.com/rails-application-templates.html), [GitHub](https://github.com/RailsApps)


## Facebook Graph API

* [Facebook Graph API](https://developers.facebook.com/docs/reference/api/)
* [`Koala` Ruby Gem](https://github.com/arsduo/koala.git)

   > Used natively for https://developers.facebook.com apps

1. **Create Facebook App**: walks you through setting up the Facbook App + starter app + automatic deployment to Heroku
2. Follow Heroku-Facebook guide: https://devcenter.heroku.com/articles/facebook
   * Create Facebook apps: "my-app" and "my-app - dev" (for local testing)
3. Read through the example source code to learn more!


#### Tutorials:
* http://rubysource.com/heroku-the-new-face-of-facebook-development/
* Sinatra Tutorial: http://rubysource.com/tag/justdoit/

#### Sample Facebook Canvas App

	https://developers.facebook.com/docs/samples/canvas/
	
Rails 3.1

[Asset Pipeline](http://guides.rubyonrails.org/asset_pipeline.html#how-to-use-the-asset-pipeline)

#### Install `Rails` v3.1

   ```bash
     $ rvm gemset create <website>
     $ rvm gemset use <website>
     $ gem install rails --version 3.1
     $ rails new <website>
     $ cd <website>
   ```

## Twitter Bootstrap

* A good overview
  http://rubysource.com/twitter-bootstrap-less-and-sass-understanding-your-options-for-rails-3-1/

#### SASS Twitter Bootstrap

1. [jlong/sass-twitter-bootstrap](https://github.com/jlong/sass-twitter-bootstrap)

   > a 1:1 translation from Less to Sass

   1. Add Twitter Bootstrap Sass CSS files to Rails project

      ```bash
        $ git clone https://github.com/jlong/sass-twitter-bootstrap.git # -> sass-twitter-bootstrap
        $ cp -r \
            "$HOME/Development/projects/github/forked/sass-twitter-bootstrap/lib/" \
            "app/assets/stylesheets/twitter-bootstrap"
      ```

   2. *Bug fix*:
         
      > Twitter Bootstrap’s Less code (and the translated Sass version) was designed to be included once using the bootstrap.scss file, which in turns includes all of the other files.

      ```bash
        $ vim app/assets/stylesheets/application.css
        - require_tree .
        + require twitter-bootstrap/bootstrap
      ```

2. [ccocchi/sass-twitter-bootstrap-rails](https://github.com/ccocchi/sass-twitter-bootstrap-rails)

3. [seyhunak/twitter-bootstrap-rails](https://github.com/seyhunak/twitter-bootstrap-rails)

   *Note: default CSS is LESS; option for SASS (out-of-box support in Rails 3 Asset Pipeline)*

    ```bash
      $ vim Gemfile
      + gem 'twitter-bootstrap-rails', "~> 2.0.8"
    ```

#### LESS Twitter Bootstrap

1. [metaskills/less-rails-bootstrap](https://github.com/metaskills/less-rails-bootstrap)



