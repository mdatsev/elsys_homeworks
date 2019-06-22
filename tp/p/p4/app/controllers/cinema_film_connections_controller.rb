class CinemaFilmConnectionsController < ApplicationController
  before_action :set_cinema_film_connection, only: [:show, :edit, :update, :destroy]

  # GET /cinema_film_connections
  # GET /cinema_film_connections.json
  def index
    @cinema_film_connections = CinemaFilmConnection.all
  end

  # GET /cinema_film_connections/1
  # GET /cinema_film_connections/1.json
  def show
  end

  # GET /cinema_film_connections/new
  def new
    @cinema_film_connection = CinemaFilmConnection.new
  end

  # GET /cinema_film_connections/1/edit
  def edit
  end

  # POST /cinema_film_connections
  # POST /cinema_film_connections.json
  def create
    @cinema_film_connection = CinemaFilmConnection.new(cinema_film_connection_params)

    respond_to do |format|
      if @cinema_film_connection.save
        format.html { redirect_to @cinema_film_connection, notice: 'Cinema film connection was successfully created.' }
        format.json { render :show, status: :created, location: @cinema_film_connection }
      else
        format.html { render :new }
        format.json { render json: @cinema_film_connection.errors, status: :unprocessable_entity }
      end
    end
  end

  # PATCH/PUT /cinema_film_connections/1
  # PATCH/PUT /cinema_film_connections/1.json
  def update
    respond_to do |format|
      if @cinema_film_connection.update(cinema_film_connection_params)
        format.html { redirect_to @cinema_film_connection, notice: 'Cinema film connection was successfully updated.' }
        format.json { render :show, status: :ok, location: @cinema_film_connection }
      else
        format.html { render :edit }
        format.json { render json: @cinema_film_connection.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /cinema_film_connections/1
  # DELETE /cinema_film_connections/1.json
  def destroy
    @cinema_film_connection.destroy
    respond_to do |format|
      format.html { redirect_to cinema_film_connections_url, notice: 'Cinema film connection was successfully destroyed.' }
      format.json { head :no_content }
    end
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_cinema_film_connection
      @cinema_film_connection = CinemaFilmConnection.find(params[:id])
    end

    # Never trust parameters from the scary internet, only allow the white list through.
    def cinema_film_connection_params
      params.require(:cinema_film_connection).permit(:cinema_id, :film_id)
    end
end
