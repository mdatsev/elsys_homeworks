class Product < ApplicationRecord
    has_many :orders
    has_many :clients, through: :orders
    validates :name, uniqueness: true
end
