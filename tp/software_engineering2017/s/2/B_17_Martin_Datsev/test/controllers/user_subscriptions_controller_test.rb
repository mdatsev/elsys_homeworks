require 'test_helper'

class UserSubscriptionsControllerTest < ActionDispatch::IntegrationTest
  setup do
    @user_subscription = user_subscriptions(:one)
  end

  test "should get index" do
    get user_subscriptions_url
    assert_response :success
  end

  test "should get new" do
    get new_user_subscription_url
    assert_response :success
  end

  test "should create user_subscription" do
    assert_difference('UserSubscription.count') do
      post user_subscriptions_url, params: { user_subscription: { role: @user_subscription.role, subscription_id: @user_subscription.subscription_id, user_id: @user_subscription.user_id } }
    end

    assert_redirected_to user_subscription_url(UserSubscription.last)
  end

  test "should show user_subscription" do
    get user_subscription_url(@user_subscription)
    assert_response :success
  end

  test "should get edit" do
    get edit_user_subscription_url(@user_subscription)
    assert_response :success
  end

  test "should update user_subscription" do
    patch user_subscription_url(@user_subscription), params: { user_subscription: { role: @user_subscription.role, subscription_id: @user_subscription.subscription_id, user_id: @user_subscription.user_id } }
    assert_redirected_to user_subscription_url(@user_subscription)
  end

  test "should destroy user_subscription" do
    assert_difference('UserSubscription.count', -1) do
      delete user_subscription_url(@user_subscription)
    end

    assert_redirected_to user_subscriptions_url
  end
end
