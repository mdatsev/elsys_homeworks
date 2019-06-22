class User < ApplicationRecord
    has_many :subscription_users
    has_many :subscriptions, through: :subscription_users
end
