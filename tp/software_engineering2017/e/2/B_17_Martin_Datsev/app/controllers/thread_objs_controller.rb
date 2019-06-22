class ThreadObjsController < ApplicationController
  before_action :set_thread_obj, only: [:show, :edit, :update, :destroy]

  # GET /thread_objs
  # GET /thread_objs.json
  def index
    @thread_objs = ThreadObj.all
  end

  # GET /thread_objs/1
  # GET /thread_objs/1.json
  def show
  end

  # GET /thread_objs/new
  def new
    @thread_obj = ThreadObj.new
  end

  # GET /thread_objs/1/edit
  def edit
  end

  # POST /thread_objs
  # POST /thread_objs.json
  def create
    @thread_obj = ThreadObj.new(thread_obj_params)

    respond_to do |format|
      if @thread_obj.save
        format.html { redirect_to @thread_obj, notice: 'Thread obj was successfully created.' }
        format.json { render :show, status: :created, location: @thread_obj }
      else
        format.html { render :new }
        format.json { render json: @thread_obj.errors, status: :unprocessable_entity }
      end
    end
  end

  # PATCH/PUT /thread_objs/1
  # PATCH/PUT /thread_objs/1.json
  def update
    respond_to do |format|
      if @thread_obj.update(thread_obj_params)
        format.html { redirect_to @thread_obj, notice: 'Thread obj was successfully updated.' }
        format.json { render :show, status: :ok, location: @thread_obj }
      else
        format.html { render :edit }
        format.json { render json: @thread_obj.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /thread_objs/1
  # DELETE /thread_objs/1.json
  def destroy
    @thread_obj.destroy
    respond_to do |format|
      format.html { redirect_to thread_objs_url, notice: 'Thread obj was successfully destroyed.' }
      format.json { head :no_content }
    end
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_thread_obj
      @thread_obj = ThreadObj.find(params[:id])
    end

    # Never trust parameters from the scary internet, only allow the white list through.
    def thread_obj_params
      params.require(:thread_obj).permit(:thread_id, :value)
    end
end
