class SumsController < ApplicationController
    def form
    end
    ColX = 0;    
    def calc
        arr = processCSVFile(params["file"]);
        render plain: "%.2f" % (arr.inject(0) {|sum, n| sum + n[ColX] }).ceil;
    end
end
