class Subscription < ApplicationRecord
	has_many :user_subscribtions
	has_many :users, through: :user_subscribtions
end
