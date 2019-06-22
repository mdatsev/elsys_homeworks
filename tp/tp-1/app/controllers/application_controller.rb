class ApplicationController < ActionController::Base
  require 'csv';
  protect_from_forgery with: :null_session
  def processCSVFile(file)
    text_file = TextFile.new({name: file.original_filename, content: file.read})
    text_file.save
    CSV.parse(text_file.content, converters: :numeric);              
  end
end
