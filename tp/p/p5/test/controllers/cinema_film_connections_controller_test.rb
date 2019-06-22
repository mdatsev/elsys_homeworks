require 'test_helper'

class CinemaFilmConnectionsControllerTest < ActionDispatch::IntegrationTest
  setup do
    @cinema_film_connection = cinema_film_connections(:one)
  end

  test "should get index" do
    get cinema_film_connections_url
    assert_response :success
  end

  test "should get new" do
    get new_cinema_film_connection_url
    assert_response :success
  end

  test "should create cinema_film_connection" do
    assert_difference('CinemaFilmConnection.count') do
      post cinema_film_connections_url, params: { cinema_film_connection: { cinema_id: @cinema_film_connection.cinema_id, film_id: @cinema_film_connection.film_id } }
    end

    assert_redirected_to cinema_film_connection_url(CinemaFilmConnection.last)
  end

  test "should show cinema_film_connection" do
    get cinema_film_connection_url(@cinema_film_connection)
    assert_response :success
  end

  test "should get edit" do
    get edit_cinema_film_connection_url(@cinema_film_connection)
    assert_response :success
  end

  test "should update cinema_film_connection" do
    patch cinema_film_connection_url(@cinema_film_connection), params: { cinema_film_connection: { cinema_id: @cinema_film_connection.cinema_id, film_id: @cinema_film_connection.film_id } }
    assert_redirected_to cinema_film_connection_url(@cinema_film_connection)
  end

  test "should destroy cinema_film_connection" do
    assert_difference('CinemaFilmConnection.count', -1) do
      delete cinema_film_connection_url(@cinema_film_connection)
    end

    assert_redirected_to cinema_film_connections_url
  end
end
