require 'test_helper'

class EncryptMessagesControllerTest < ActionController::TestCase
  setup do
    @rsa = rsas(:one)
    @encrypt_message = encrypt_messages(:one)
  end

  test "should get index" do
    get :index, params: { rsa_id: @rsa }
    assert_response :success
  end

  test "should get new" do
    get :new, params: { rsa_id: @rsa }
    assert_response :success
  end

  test "should create encrypt_message" do
    assert_difference('EncryptMessage.count') do
      post :create, params: { rsa_id: @rsa, encrypt_message: @encrypt_message.attributes }
    end

    assert_redirected_to rsa_encrypt_message_path(@rsa, EncryptMessage.last)
  end

  test "should show encrypt_message" do
    get :show, params: { rsa_id: @rsa, id: @encrypt_message }
    assert_response :success
  end

  test "should get edit" do
    get :edit, params: { rsa_id: @rsa, id: @encrypt_message }
    assert_response :success
  end

  test "should update encrypt_message" do
    put :update, params: { rsa_id: @rsa, id: @encrypt_message, encrypt_message: @encrypt_message.attributes }
    assert_redirected_to rsa_encrypt_message_path(@rsa, EncryptMessage.last)
  end

  test "should destroy encrypt_message" do
    assert_difference('EncryptMessage.count', -1) do
      delete :destroy, params: { rsa_id: @rsa, id: @encrypt_message }
    end

    assert_redirected_to rsa_encrypt_messages_path(@rsa)
  end
end
