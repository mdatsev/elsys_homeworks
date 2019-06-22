class FiltersController < ApplicationController  
    def form
    end
    ColY = 1;
    ColZ = 2;
    def calc
        arr = processCSVFile(params["file"]);   
        render plain: "%.2f" % (arr.inject(0) {|sum, n| sum + (!n[ColZ].nil? ? (n[ColZ] % 2 == 1 ? n[ColY] : 0) : 0)}).ceil;
    end
end
