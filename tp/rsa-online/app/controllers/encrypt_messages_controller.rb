class EncryptMessagesController < ApplicationController
  before_action :set_encrypt_messages
  before_action :set_encrypt_message, only: [:show, :edit, :update, :destroy]

  # GET rsas/1/encrypt_messages
  #def index
  #  @encrypt_messages = @rsa.encrypt_messages
  #end

  # GET rsas/1/encrypt_messages/1
  def show
    render json: {message: @encrypt_message.message}
  end

  # GET rsas/1/encrypt_messages/new
  #def new
  #  @encrypt_message = @rsa.encrypt_messages.build
  #end

  # GET rsas/1/encrypt_messages/1/edit
  #def edit
  #end

  # POST rsas/1/encrypt_messages
  def create
    rsa = RSA.new(@rsa.n, @rsa.e, @rsa.d)
    @encrypt_message = @rsa.encrypt_messages.build({message: rsa.encrypt(params[:message])})
    @encrypt_message.save
    render json: @encrypt_message.id
  end

  # PUT rsas/1/encrypt_messages/1
  #def update
  #  if @encrypt_message.update_attributes(encrypt_message_params)
  #    redirect_to([@encrypt_message.rsa, @encrypt_message], notice: 'Encrypt message was successfully updated.')
  #  else
  #    render action: 'edit'
  #  end
  #end

  # DELETE rsas/1/encrypt_messages/1
  #def destroy
  #  @encrypt_message.destroy

  #  redirect_to rsa_encrypt_messages_url(@rsa)
  #end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_encrypt_messages
      @rsa = Rsa.find(params[:rsa_id])
    end

    def set_encrypt_message
      @encrypt_message = @rsa.encrypt_messages.find(params[:id])
    end

    # Only allow a trusted parameter "white list" through.
    #def encrypt_message_params
    #  params.require(:encrypt_message).permit(:message)
    #end
end
