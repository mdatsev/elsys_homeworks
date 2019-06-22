require 'test_helper'

class TextFilesControllerTest < ActionDispatch::IntegrationTest
  setup do
    @text_file = text_files(:one)
  end

  test "should get index" do
    get text_files_url
    assert_response :success
  end

  test "should get new" do
    get new_text_file_url
    assert_response :success
  end

  test "should create text_file" do
    assert_difference('TextFile.count') do
      post text_files_url, params: { text_file: { content: @text_file.content, name: @text_file.name } }
    end

    assert_redirected_to text_file_url(TextFile.last)
  end

  test "should show text_file" do
    get text_file_url(@text_file)
    assert_response :success
  end

  test "should get edit" do
    get edit_text_file_url(@text_file)
    assert_response :success
  end

  test "should update text_file" do
    patch text_file_url(@text_file), params: { text_file: { content: @text_file.content, name: @text_file.name } }
    assert_redirected_to text_file_url(@text_file)
  end

  test "should destroy text_file" do
    assert_difference('TextFile.count', -1) do
      delete text_file_url(@text_file)
    end

    assert_redirected_to text_files_url
  end
end
