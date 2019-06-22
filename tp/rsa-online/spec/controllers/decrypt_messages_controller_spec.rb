RSpec.describe DecryptMessagesController do 
    fixtures :rsas
    fixtures :decrypt_messages
    
    it "creates a message" do
        post :create, params: {rsa_id: rsas(:wikipedia).id, message: "kp-19c-h0-j6-2gb"}
        expect(DecryptMessage.where(id: response.body.to_i)).to exist
    end

    it "creates message that is correctly decrypted" do
        fix_rsa = rsas(:wikipedia)
        post :create, params: {rsa_id: fix_rsa.id, message: "1oa-10h-kp-kp-1op"}
        msg = DecryptMessage.find_by(id: response.body.to_i)
        expect(RSA.new(fix_rsa.n, fix_rsa.e, fix_rsa.d).decrypt("1oa-10h-kp-kp-1op")).to eq msg.message
    end

    it "retrieves a message by id" do
        fix_msg = decrypt_messages(:hello);
        get :show, params: {rsa_id: fix_msg.rsa.id, id: fix_msg.id}
        json = JSON.parse(response.body)
        expect(json["message"]).to eq fix_msg.message
    end

end