require_relative '../lib/RSA'

RSpec.describe RSA do
    it "should preserve the message encrypt->decrypt with keys 3233, 17, 413" do
        rsa = RSA.new(3233, 17, 413)
        expect(rsa.decrypt(rsa.encrypt("henlo"))).to eq "henlo"
    end
    it "encrypted message should not be the same" do
        rsa = RSA.new(*RSA.new_key)
        expect(rsa.encrypt("henlo")).not_to eq "henlo"
    end
    it "should preserve the message enctypt->decrypt with generated key" do
        rsa = RSA.new(*RSA.new_key)
        expect(rsa.decrypt(rsa.encrypt("henlo"))).to eq "henlo"
    end
    it "should return the right n" do
        rsa = RSA.new(123,0,0)
        expect(rsa.n).to eq 123
    end
    it "should return the right e" do
        rsa = RSA.new(0,321,0)
        expect(rsa.e).to eq 321
    end
    it "should return the right d" do
        rsa = RSA.new(0,0,567)
        expect(rsa.d).to eq 567
    end
    it "should encrypt this basic test" do
        rsa = RSA.new(627,241,49)
        expect(rsa.encrypt("a")).to eq "ay"
    end
end