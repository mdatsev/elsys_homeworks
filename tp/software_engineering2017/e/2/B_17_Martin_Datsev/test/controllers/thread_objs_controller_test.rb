require 'test_helper'

class ThreadObjsControllerTest < ActionDispatch::IntegrationTest
  setup do
    @thread_obj = thread_objs(:one)
  end

  test "should get index" do
    get thread_objs_url
    assert_response :success
  end

  test "should get new" do
    get new_thread_obj_url
    assert_response :success
  end

  test "should create thread_obj" do
    assert_difference('ThreadObj.count') do
      post thread_objs_url, params: { thread_obj: { thread_id: @thread_obj.thread_id, value: @thread_obj.value } }
    end

    assert_redirected_to thread_obj_url(ThreadObj.last)
  end

  test "should show thread_obj" do
    get thread_obj_url(@thread_obj)
    assert_response :success
  end

  test "should get edit" do
    get edit_thread_obj_url(@thread_obj)
    assert_response :success
  end

  test "should update thread_obj" do
    patch thread_obj_url(@thread_obj), params: { thread_obj: { thread_id: @thread_obj.thread_id, value: @thread_obj.value } }
    assert_redirected_to thread_obj_url(@thread_obj)
  end

  test "should destroy thread_obj" do
    assert_difference('ThreadObj.count', -1) do
      delete thread_obj_url(@thread_obj)
    end

    assert_redirected_to thread_objs_url
  end
end
