require 'test_helper'

class RsasControllerTest < ActionDispatch::IntegrationTest
  setup do
    @rsa = rsas(:one)
  end

  test "should get index" do
    get rsas_url
    assert_response :success
  end

  test "should get new" do
    get new_rsa_url
    assert_response :success
  end

  test "should create rsa" do
    assert_difference('Rsa.count') do
      post rsas_url, params: { rsa: { d: @rsa.d, e: @rsa.e, n: @rsa.n } }
    end

    assert_redirected_to rsa_url(Rsa.last)
  end

  test "should show rsa" do
    get rsa_url(@rsa)
    assert_response :success
  end

  test "should get edit" do
    get edit_rsa_url(@rsa)
    assert_response :success
  end

  test "should update rsa" do
    patch rsa_url(@rsa), params: { rsa: { d: @rsa.d, e: @rsa.e, n: @rsa.n } }
    assert_redirected_to rsa_url(@rsa)
  end

  test "should destroy rsa" do
    assert_difference('Rsa.count', -1) do
      delete rsa_url(@rsa)
    end

    assert_redirected_to rsas_url
  end
end
