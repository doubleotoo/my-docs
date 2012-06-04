rails-docs
==========

## Rails Application Templates
* RailsApps [Website](http://railsapps.github.com/rails-application-templates.html), [GitHub](https://github.com/RailsApps)


## Manage Data

* [sferik/rails_admin](https://github.com/sferik/rails_admin)

  > a Rails 3 engine that provides an easy-to-use interface for managing your data



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

* A good overview of different ways to integrate Twitter Bootstrap + Rails
  http://rubysource.com/twitter-bootstrap-less-and-sass-understanding-your-options-for-rails-3-1/

#### SASS Twitter Bootstrap

1. **[thomas-mcdonald/bootstrap-sass](https://github.com/thomas-mcdonald/bootstrap-sass)**

   ```bash
     $ vim Gemfile
     ...
     gem 'sass-rails', " ~> 3.1.0"
     + gem 'bootstrap-sass', '~> 2.0.3'
     
     $ bundle install
   ```
   
   ```bash
     $ mv app/assets/stylesheets/application.css app/assets/stylesheets/application.css.scss
     $ vim app/assets/stylesheets/application.css.scss
     
     /*
      * You're free to add application-wide styles to this file and they'll appear at
      * the top of the compiled file, but it's generally better to create a new file per style scope.
      *= require_self      
      */

      @import "bootstrap"; // <-- Add this, remove `*= require_tree .` from the top ^
   ```
   
   *Reference: https://github.com/sferik/rails_admin/blob/master/app/assets/stylesheets/rails_admin/imports.css.scss.erb*

   * Create a controller for the Application root/index:
    
     ```bash
       $ rm public/index.html
       $ rails generate controller main index
       $ vim config/routes.rb
       + root :to => 'main#index'
     ```

2. [anjlab/bootstrap-rails](https://github.com/anjlab/bootstrap-rails)

3. [jlong/sass-twitter-bootstrap](https://github.com/jlong/sass-twitter-bootstrap)

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

4. [ccocchi/sass-twitter-bootstrap-rails](https://github.com/ccocchi/sass-twitter-bootstrap-rails)

5. [seyhunak/twitter-bootstrap-rails](https://github.com/seyhunak/twitter-bootstrap-rails)

   *Note: default CSS is LESS; option for SASS (out-of-box support in Rails 3 Asset Pipeline)*

    ```bash
      $ vim Gemfile
      + gem 'twitter-bootstrap-rails', "~> 2.0.8"
    ```

#### LESS Twitter Bootstrap

1. [metaskills/less-rails-bootstrap](https://github.com/metaskills/less-rails-bootstrap)



