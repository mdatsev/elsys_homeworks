class Rsa < ApplicationRecord
  has_many :decrypt_messages
  has_many :encrypt_messages
end
