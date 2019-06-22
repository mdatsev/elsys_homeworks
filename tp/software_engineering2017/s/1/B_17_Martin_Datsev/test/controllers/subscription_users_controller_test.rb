require 'test_helper'

class SubscriptionUsersControllerTest < ActionDispatch::IntegrationTest
  setup do
    @subscription_user = subscription_users(:one)
  end

  test "should get index" do
    get subscription_users_url
    assert_response :success
  end

  test "should get new" do
    get new_subscription_user_url
    assert_response :success
  end

  test "should create subscription_user" do
    assert_difference('SubscriptionUser.count') do
      post subscription_users_url, params: { subscription_user: { position: @subscription_user.position, subscription_id: @subscription_user.subscription_id, user_id: @subscription_user.user_id } }
    end

    assert_redirected_to subscription_user_url(SubscriptionUser.last)
  end

  test "should show subscription_user" do
    get subscription_user_url(@subscription_user)
    assert_response :success
  end

  test "should get edit" do
    get edit_subscription_user_url(@subscription_user)
    assert_response :success
  end

  test "should update subscription_user" do
    patch subscription_user_url(@subscription_user), params: { subscription_user: { position: @subscription_user.position, subscription_id: @subscription_user.subscription_id, user_id: @subscription_user.user_id } }
    assert_redirected_to subscription_user_url(@subscription_user)
  end

  test "should destroy subscription_user" do
    assert_difference('SubscriptionUser.count', -1) do
      delete subscription_user_url(@subscription_user)
    end

    assert_redirected_to subscription_users_url
  end
end
