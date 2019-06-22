class ThreadObjectsController < ApplicationController
  before_action :set_thread_object, only: [:show, :edit, :update, :destroy]

  # GET /thread_objects
  # GET /thread_objects.json
  def index
    @thread_objects = ThreadObject.all
  end

  # GET /thread_objects/1
  # GET /thread_objects/1.json
  def show
  end

  # GET /thread_objects/new
  def new
    @thread_object = ThreadObject.new
  end

  # GET /thread_objects/1/edit
  def edit
  end

  # POST /thread_objects
  # POST /thread_objects.json
  def create
    @thread_object = ThreadObject.new(thread_object_params)

    respond_to do |format|
      if @thread_object.save
        format.html { redirect_to @thread_object, notice: 'Thread object was successfully created.' }
        format.json { render :show, status: :created, location: @thread_object }
      else
        format.html { render :new }
        format.json { render json: @thread_object.errors, status: :unprocessable_entity }
      end
    end
  end

  # PATCH/PUT /thread_objects/1
  # PATCH/PUT /thread_objects/1.json
  def update
    respond_to do |format|
      if @thread_object.update(thread_object_params)
        format.html { redirect_to @thread_object, notice: 'Thread object was successfully updated.' }
        format.json { render :show, status: :ok, location: @thread_object }
      else
        format.html { render :edit }
        format.json { render json: @thread_object.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /thread_objects/1
  # DELETE /thread_objects/1.json
  def destroy
    @thread_object.destroy
    respond_to do |format|
      format.html { redirect_to thread_objects_url, notice: 'Thread object was successfully destroyed.' }
      format.json { head :no_content }
    end
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_thread_object
      @thread_object = ThreadObject.find(params[:id])
    end

    # Never trust parameters from the scary internet, only allow the white list through.
    def thread_object_params
      params.require(:thread_object).permit(:id, :value)
    end
end
