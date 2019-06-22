class User < ApplicationRecord
	has_many :user_subscribtions
	has_many :subscriptions, through: :user_subscribtion
end
