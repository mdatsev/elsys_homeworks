require "prime"

def twoprimes
    Prime.first(100).drop(60).shuffle[0..1]
end

def invmod(a, m)
  i = 0
  loop do
    if a * i % m == 1
      return i
    end
    i+=1
  end
end

class RSA
    def initialize n, e, d
        @n = n
        @e = e
        @d = d
      #initializes this instance of RSA with a n,e and d variables of type int. 'n','e' are the public key and 'd' is the private one. This n,e,d should be used when encrypting and decrypting the message
    end
    
    def n
      @n
    end
    
    def e
      @e
    end
    
    def d
      @d
    end
    
    def new_key
        p, q = twoprimes
        n = p*q
        ctfn = (p-1).lcm(q-1)
        e = e
        loop do
            e = rand(1...ctfn)
            break if e.gcd(ctfn) == 1
        end
        d = invmod(e, ctfn)
        [n, e, d]
       #generates a new 'n','e' and 'd' values following the RSA algorithm. Returns a new array of three elements where the first element is 'n', the second is 'e' and the third is 'd'. Each time it is called a new key must be returned.
    end
    
    def encrypt message
      message.chars.map { |ch| (ch.ord ** @e % @n).to_s(36) }.join('-')
      #encrypts the message passed. The message is of type string. Encrypts each symbol of this string by using its ASCII number representation and returns the encrypted message.
    end
    
    def decrypt message
      message.split("-").map { |seg| (seg.to_i(36) ** @d % @n).chr }.join('')
      #decrypts the message passed. The message is of type string. Decrypts each symbol of this string Encrypts each symbol of this string by using its ASCII number representationand returns the decrypted message. 
    end
end