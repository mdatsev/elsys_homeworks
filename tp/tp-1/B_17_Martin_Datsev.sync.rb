class String
    def red;            "\e[31m#{self}\e[0m" end
    def green;          "\e[32m#{self}\e[0m" end
    def brown;          "\e[33m#{self}\e[0m" end 
end
require 'csv'
require 'time'

Tests = [
    {
        filePath: "./B_17_Martin_Datsev.csv",
        requests:[
            {
                url: "/sums",
                response: "11.00"
            },
            {
                url: "/intervals",
                response: "11.00"
            },
            {
                url: "/filters",
                response: "8.00"
            },
            {
                url: "/lin_regressions",
                response: "1.100000,0.000000"
            }
        ]
    },
    {
        filePath: "./B_17_Martin_Datsev_2.csv",
        requests:[
            {
                url: "/sums",
                response: "-96932640.00"
            },
            {
                url: "/intervals",
                response: "1803740.00"
            },
            {
                url: "/filters",
                response: "3630.00"
            },
            {
                url: "/lin_regressions",
                response: "9424.559462,-1377957.847479"
            }
        ]
    }
]

DeadLine = DateTime.parse("10/10/2017 23:59:59");

csv_text = File.read(ARGV[0])
csv = CSV.parse(csv_text, :headers => true)

students = [];

csv.each do |row|
    unless row[2].nil? && row[3].nil? && row[4].nil?
        late = ((DateTime.parse(row[0]) - DeadLine)* 24 * 60 * 60).to_i;
        students.push({
            late: late > 0 ? "(#{late} minutes late)" : "",
            klas: row[1] =~ /[bBбБ]/ ? "B" : ( row[1] =~ /[aAаА]/ ? "A" : "?"),    
            number: row[2],            
            name: row[3].to_s + " " + row[4].to_s,
            hurl: row[5],
            done: false
        })
    end
end

students.sort_by! {|s| [s[:klas].to_s, s[:number].to_i] }

ReqMaxTime = 10;

Thread.abort_on_exception=true
students.each do |s|
    #Thread.new do
        result = "1"
        Tests.each do |test| 
            test[:requests].each do |req|
                res = `curl --form \"file=@#{test[:filePath]}\" #{s[:hurl]}#{req[:url]} 2>/dev/null -m #{ReqMaxTime}`;        
                if(res != req[:response])
                    result = "0";
                    break;
                end
                #s[:timeout] = res.start_with?("curl: (28)") ? "(request timeout)" : "asdfsadf";
            end
        end
        s[:done] = true;
        row = sprintf "%s%02d %s %s\t%s\n", s[:klas], s[:number], s[:name].ljust(22), result, s[:late]
        if result == "0"
            printf row.red
        elsif s[:late] != ""
            printf row.brown
        else 
            printf row.green
        end
        if students.all? {|t| t[:done] }
            exit
        end
        printf students.select{|t| t[:done]}.size.to_s + "/" + students.size.to_s + "\r";
    #end
end

sleep