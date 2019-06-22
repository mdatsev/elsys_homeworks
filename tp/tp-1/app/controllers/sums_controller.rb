class SumsController < ApplicationController
    require 'csv';
    def form
    end
    ColX = 0;    
    def calc
        arr = CSV.parse(params["file"].read, converters: :numeric)#parse file into array of arrays of numbers 
        sum = 0
        for i in 0..arr.length - 1
            sum += arr[i][0] #for each row add the first element
        end
        render plain: "%.2f" % sum.ceil #ceil and format to 2 decimal places
    end
end
