class Cezar
    def encode(str, shift)
        str.chars.map{|x| 
            code = x.ord + shift
            if(code > 'z'.ord)
                code -= 26
            elsif(code < 'a'.ord && code > 'Z'.ord && shift > 0)
                code -= 26
            elsif(code < 'A'.ord)
                code += 26
            elsif(code < 'a'.ord && code > 'Z'.ord && shift < 0)
                code += 26
            end
            code.chr
        }.join("")
    end
    def decode(str, shift)
        encode(str, -shift)
    end
end

describe Cezar do
    cz = Cezar.new 
    it "encode('abc', 1) should return 'bcd'" do
        result = cz.encode("abc", 1)
        expect(result).to eq "bcd"
    end
    it "decode('bcd', 1) should return 'abc'" do
        result = cz.decode("bcd", 1)
        expect(result).to eq "abc"
    end
    it "encode('zzz', 1) should return 'aaa'" do
        result = cz.encode("zzz", 1)        
        expect(result).to eq "aaa"
    end
    it "encode('ZZZ', 1) should return 'AAA'" do
        result = cz.encode("ZZZ", 1)        
        expect(result).to eq "AAA"
    end
    it "encode('ZzaB', 1) should return 'AabC'" do
        result = cz.encode("ZzaB", 1)        
        expect(result).to eq "AabC"
    end
    it "decode('AAA', 1) should return 'ZZZ'" do
        result = cz.decode("AAA", 1)        
        expect(result).to eq "ZZZ"
    end
    it "decode('aaa', 1) should return 'zzz'" do
        result = cz.decode("aaa", 1)        
        expect(result).to eq "zzz"
    end
end
