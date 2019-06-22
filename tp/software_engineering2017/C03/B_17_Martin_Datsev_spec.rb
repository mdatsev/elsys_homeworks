class Caesar
    def encrypt(str, shift)
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
            if(x !~ /[[:alpha:]]/)
                x
            else
                code.chr
            end
        }.join("")
    end
    def decrypt(str, shift)
        encrypt(str, -shift)
    end
end

describe Caesar do
    cz = Caesar.new 
    it "encrypt('abc', 1) should return 'bcd'" do
        result = cz.encrypt("abc", 1)
        expect(result).to eq "bcd"
    end
    it "decrypt('bcd', 1) should return 'abc'" do
        result = cz.decrypt("bcd", 1)
        expect(result).to eq "abc"
    end
    it "encrypt('zzz', 1) should return 'aaa'" do
        result = cz.encrypt("zzz", 1)        
        expect(result).to eq "aaa"
    end
    it "encrypt('ZZZ', 1) should return 'AAA'" do
        result = cz.encrypt("ZZZ", 1)        
        expect(result).to eq "AAA"
    end
    it "encrypt('ZzaB', 1) should return 'AabC'" do
        result = cz.encrypt("ZzaB", 1)        
        expect(result).to eq "AabC"
    end
    it "decrypt('AAA', 1) should return 'ZZZ'" do
        result = cz.decrypt("AAA", 1)        
        expect(result).to eq "ZZZ"
    end
    it "decrypt('aaa', 1) should return 'zzz'" do
        result = cz.decrypt("aaa", 1)        
        expect(result).to eq "zzz"
    end
    it "decrypt('Lorem ipsum dolor sit amet.1234', 20) should return 'Filyg cjmog xifil mcn ugyn.1234'" do
        result = cz.encrypt("Lorem ipsum dolor sit amet.1234", 20)        
        expect(result).to eq "Filyg cjmog xifil mcn ugyn.1234"
    end
    it "decrypt(encrypt('DxSGeKNSl1dA0wxPhju9', 3), 3) should be equal to 'DxSGeKNSl1dA0wxPhju9'" do
        result = cz.decrypt(cz.encrypt("DxSGeKNSl1dA0wxPhju9", 3), 3)
        expect(result).to eq           "DxSGeKNSl1dA0wxPhju9"
    end
end
