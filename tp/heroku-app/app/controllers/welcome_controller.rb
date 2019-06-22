class WelcomeController < ApplicationController
  def index
  
  end


  def upload
    recieved_file = params[:file].read;
    @file = recieved_file;
    render "csvview";
  end
end