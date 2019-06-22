class Subscription < ApplicationRecord
    has_many :subscription_users
    has_many :users, through: :subscription_users
end
