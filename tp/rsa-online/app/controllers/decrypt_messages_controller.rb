class DecryptMessagesController < ApplicationController
  before_action :set_decrypt_messages
  before_action :set_decrypt_message, only: [:show, :edit, :update, :destroy]

  ## GET rsas/1/decrypt_messages
  #def index
  #  @decrypt_messages = @rsa.decrypt_messages
  #end

  # GET rsas/1/decrypt_messages/1
  def show
    render json: {message: @decrypt_message.message}
  end

  ## GET rsas/1/decrypt_messages/new
  #def new
  #  @decrypt_message = @rsa.decrypt_messages.build
  #end

  ## GET rsas/1/decrypt_messages/1/edit
  #def edit
  #end

  # POST rsas/1/decrypt_messages
  def create
    rsa = RSA.new(@rsa.n, @rsa.e, @rsa.d)
    @decrypt_message = @rsa.decrypt_messages.build({message: rsa.decrypt(params[:message])})

    @decrypt_message.save
    render json: @decrypt_message.id
    end

  # PUT rsas/1/decrypt_messages/1
  #def update
  #  if @decrypt_message.update_attributes(decrypt_message_params)
  #    redirect_to([@decrypt_message.rsa, @decrypt_message], notice: 'Decrypt message was successfully updated.')
  #  else
  #    render action: 'edit'
  #  end
  #end

  # DELETE rsas/1/decrypt_messages/1
  #def destroy
  #  @decrypt_message.destroy
#
  #  redirect_to rsa_decrypt_messages_url(@rsa)
  #end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_decrypt_messages
      @rsa = Rsa.find(params[:rsa_id])
    end

    def set_decrypt_message
      @decrypt_message = @rsa.decrypt_messages.find(params[:id])
    end

    # Only allow a trusted parameter "white list" through.
    #def decrypt_message_params
    #  params.require(:decrypt_message).permit(:message)
    #end
end
