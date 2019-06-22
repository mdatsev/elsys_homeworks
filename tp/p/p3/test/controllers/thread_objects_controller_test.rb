require 'test_helper'

class ThreadObjectsControllerTest < ActionDispatch::IntegrationTest
  setup do
    @thread_object = thread_objects(:one)
  end

  test "should get index" do
    get thread_objects_url
    assert_response :success
  end

  test "should get new" do
    get new_thread_object_url
    assert_response :success
  end

  test "should create thread_object" do
    assert_difference('ThreadObject.count') do
      post thread_objects_url, params: { thread_object: { id: @thread_object.id, value: @thread_object.value } }
    end

    assert_redirected_to thread_object_url(ThreadObject.last)
  end

  test "should show thread_object" do
    get thread_object_url(@thread_object)
    assert_response :success
  end

  test "should get edit" do
    get edit_thread_object_url(@thread_object)
    assert_response :success
  end

  test "should update thread_object" do
    patch thread_object_url(@thread_object), params: { thread_object: { id: @thread_object.id, value: @thread_object.value } }
    assert_redirected_to thread_object_url(@thread_object)
  end

  test "should destroy thread_object" do
    assert_difference('ThreadObject.count', -1) do
      delete thread_object_url(@thread_object)
    end

    assert_redirected_to thread_objects_url
  end
end
