class SubscriptionUsersController < ApplicationController
  before_action :set_subscription_user, only: [:show, :edit, :update, :destroy]

  # GET /subscription_users
  # GET /subscription_users.json
  def index
    @subscription_users = SubscriptionUser.all
  end

  # GET /subscription_users/1
  # GET /subscription_users/1.json
  def show
  end

  # GET /subscription_users/new
  def new
    @subscription_user = SubscriptionUser.new
  end

  # GET /subscription_users/1/edit
  def edit
  end

  # POST /subscription_users
  # POST /subscription_users.json
  def create
    @subscription_user = SubscriptionUser.new(subscription_user_params)

    respond_to do |format|
      if @subscription_user.save
        format.html { redirect_to @subscription_user, notice: 'Subscription user was successfully created.' }
        format.json { render :show, status: :created, location: @subscription_user }
      else
        format.html { render :new }
        format.json { render json: @subscription_user.errors, status: :unprocessable_entity }
      end
    end
  end

  # PATCH/PUT /subscription_users/1
  # PATCH/PUT /subscription_users/1.json
  def update
    respond_to do |format|
      if @subscription_user.update(subscription_user_params)
        format.html { redirect_to @subscription_user, notice: 'Subscription user was successfully updated.' }
        format.json { render :show, status: :ok, location: @subscription_user }
      else
        format.html { render :edit }
        format.json { render json: @subscription_user.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /subscription_users/1
  # DELETE /subscription_users/1.json
  def destroy
    @subscription_user.destroy
    respond_to do |format|
      format.html { redirect_to subscription_users_url, notice: 'Subscription user was successfully destroyed.' }
      format.json { head :no_content }
    end
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_subscription_user
      @subscription_user = SubscriptionUser.find(params[:id])
    end

    # Never trust parameters from the scary internet, only allow the white list through.
    def subscription_user_params
      params.require(:subscription_user).permit(:position, :user_id, :subscription_id)
    end
end
