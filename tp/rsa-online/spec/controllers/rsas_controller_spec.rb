RSpec.describe RsasController do 
    
    fixtures :rsas

    it "creates an rsa" do
        post :create
        id = response.body.to_i
        expect(Rsa.where(id: id)).to exist
    end

    it "creates an rsa with valid keys" do
        post :create
        id = response.body.to_i
        expect(Rsa.where(id: id)).to exist
        rsa_record = Rsa.find_by(id: id)
        rsa = RSA.new(rsa_record.n, rsa_record.e, rsa_record.d)
        expect(rsa.decrypt(rsa.encrypt("hello"))).to eq "hello"
    end

    it "creates an rsa with keys" do
        post :create, params: {n: 1, e: 2, d: 3}
        id = response.body.to_i
        rsa = Rsa.find_by(id: id)
        expect(rsa.n.to_i).to eq 1
        expect(rsa.e.to_i).to eq 2
        expect(rsa.d.to_i).to eq 3
    end

    it "creates an rsa with big keys" do
        post :create, params: {n: 100_000, e: 100_000_000_000, d: 999_999_999_999_999_999_999_999_999_999_999}
        id = response.body.to_i
        expect(Rsa.where(id: id)).to exist
        rsa = Rsa.find_by(id: id)
        expect(rsa.n.to_i).to eq 100_000
        expect(rsa.e.to_i).to eq 100_000_000_000
        expect(rsa.d.to_i).to eq 999_999_999_999_999_999_999_999_999_999_999
    end

    it "retrieves an rsa record by id" do
        fix_rsa = rsas(:wikipedia)
        get :show, params: {id: fix_rsa.id}
        json = JSON.parse(response.body)
        expect(json["n"]).to eq fix_rsa.n
        expect(json["e"]).to eq fix_rsa.e
        expect(json["d"]).to eq fix_rsa.d
    end

end