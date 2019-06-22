class UserSubscription < ApplicationRecord
	belongs_to :user
	belongs_to :subscription
	#validates :user_id, uniqueness: { scope: :subscription_id,
    #message: "This role for that subscriptions is already taken by this users" }
end
