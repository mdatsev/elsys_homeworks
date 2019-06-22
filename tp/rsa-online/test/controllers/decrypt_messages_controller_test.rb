require 'test_helper'

class DecryptMessagesControllerTest < ActionController::TestCase
  setup do
    @rsa = rsas(:one)
    @decrypt_message = decrypt_messages(:one)
  end

  test "should get index" do
    get :index, params: { rsa_id: @rsa }
    assert_response :success
  end

  test "should get new" do
    get :new, params: { rsa_id: @rsa }
    assert_response :success
  end

  test "should create decrypt_message" do
    assert_difference('DecryptMessage.count') do
      post :create, params: { rsa_id: @rsa, decrypt_message: @decrypt_message.attributes }
    end

    assert_redirected_to rsa_decrypt_message_path(@rsa, DecryptMessage.last)
  end

  test "should show decrypt_message" do
    get :show, params: { rsa_id: @rsa, id: @decrypt_message }
    assert_response :success
  end

  test "should get edit" do
    get :edit, params: { rsa_id: @rsa, id: @decrypt_message }
    assert_response :success
  end

  test "should update decrypt_message" do
    put :update, params: { rsa_id: @rsa, id: @decrypt_message, decrypt_message: @decrypt_message.attributes }
    assert_redirected_to rsa_decrypt_message_path(@rsa, DecryptMessage.last)
  end

  test "should destroy decrypt_message" do
    assert_difference('DecryptMessage.count', -1) do
      delete :destroy, params: { rsa_id: @rsa, id: @decrypt_message }
    end

    assert_redirected_to rsa_decrypt_messages_path(@rsa)
  end
end
