class String
    def red;            "\e[31m#{self}\e[0m" end
    def green;          "\e[32m#{self}\e[0m" end
    def brown;          "\e[33m#{self}\e[0m" end 
end

require 'csv'
require 'time'

TempFilePath = "./temp.csv";

testfile = CSV.parse(File.read(ARGV[1]))

open(TempFilePath, 'w') { |f|
    testfile.drop(1).each do |row|
        f.puts row.join(",")
    end
}

fixtures_header = testfile[0]

Tests = [
    {
        filePath: TempFilePath,
        requests:[
            {
                url: "/sums",
                response: fixtures_header[0]
            },
            {
                url: "/filters",
                response: fixtures_header[1]
            },
            {
                url: "/intervals",
                response: fixtures_header[2]
            },
            {
                url: "/lin_regressions",
                response: fixtures_header[3]
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
            late: late > 0 ? "(#{late} seconds late)" : "",
            klas: row[1] =~ /[bBбБ]/ ? "B" : ( row[1] =~ /[aAаА]/ ? "A" : "?"),    
            number: row[2],            
            name: row[3].to_s + "," + row[4].to_s,
            hurl: row[5],
            done: false
        })
    end
end

ReqMaxTime = 15;

Thread.abort_on_exception=true
students.each do |s|
    Thread.new do
        result = "1"
        Tests.each do |test| 
            test[:requests].each do |req|
                res = `curl --form \"file=@#{test[:filePath]}\" #{s[:hurl]}#{req[:url]} 2>/dev/null -m #{ReqMaxTime}`;
                if(res != req[:response])
                    result = "0";
                    break;
                end
            end
        end
        s[:done] = true;
        s[:row] = sprintf "%s,%02d,%s,%s\n", s[:klas], s[:number], s[:name], result
        print result == "1" ? s[:row].green : s[:row].red
        if students.all? {|t| t[:done] }
            open("./B_17_Martin_Datsev_results.csv", 'w') { |f|
                students.sort_by! {|s| [s[:klas].to_s, s[:number].to_i] }
                students.each do |o|
                    f.print o[:row]
                end
            }
            File.delete(TempFilePath)
            exit
        end
        printf students.select{|t| t[:done]}.size.to_s + "/" + students.size.to_s + "\r";
    end
end

sleep