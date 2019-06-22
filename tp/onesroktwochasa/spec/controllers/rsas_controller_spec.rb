RSpec.describe RsasController do 

    it "gets by id" do
        get :show, params: {id: 1}
        expect(response.body.to_s).to eq "the content"
    end

end