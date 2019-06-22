require_relative '../lib/rome_converter'

RSpec.describe RomeConverter do
    conversion_table = 
    [
        [1,"I"],
        [2,"II"],
        [3,"III"],
        [4,"IV"],
        [5,"V"],
        [6,"VI"],
        [7,"VII"],
        [8,"VIII"],
        [9,"IX"],
        [10,"X"],
        [49,"XLIX"],
        [50,"L"],
        [99,"XCIX"],
        [100,"C"],
        [499,"CDXCIX"],
        [500,"D"],
        [999,"CMXCIX"],
        [1000,"M"],
        [4999,"MMMMCMXCIX"],
        [88,"LXXXVIII"],
        #[5000,"MMMMM"],
        #[9888,"MMMMMMMMMDCCCLXXXVIII"]
    ]

    conversion_table.each do |row|
        it "to_rome should convert #{row[0]} to #{row[1]}" do
            expect(described_class.new.to_rome row[0]).to eq row[1]
        end
    end
    conversion_table.each do |row|
        it "to_dec should convert #{row[1]} to #{row[0]}" do
            expect(described_class.new.to_dec row[1]).to eq row[0]
        end
    end
end