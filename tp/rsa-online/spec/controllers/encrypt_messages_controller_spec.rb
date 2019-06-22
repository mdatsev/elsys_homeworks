RSpec.describe EncryptMessagesController do 
    fixtures :rsas
    fixtures :encrypt_messages
    
    it "creates a message" do
        post :create, params: {rsa_id: rsas(:wikipedia).id, message: "zdr"}
        expect(EncryptMessage.where(id: response.body.to_i)).to exist
    end

    it "creates message that is correctly encrypted" do
        fix_rsa = rsas(:wikipedia)
        post :create, params: {rsa_id: fix_rsa.id, message: "hola"}
        msg = EncryptMessage.find_by(id: response.body.to_i)
        expect(RSA.new(fix_rsa.n, fix_rsa.e, fix_rsa.d).encrypt("hola")).to eq msg.message
    end

    it "retrieves a message by id" do
        fix_msg = encrypt_messages(:hello);
        get :show, params: {rsa_id: fix_msg.rsa.id, id: fix_msg.id}
        json = JSON.parse(response.body)
        expect(json["message"]).to eq fix_msg.message
    end

end