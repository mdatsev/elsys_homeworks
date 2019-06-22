class ThreadObject < ApplicationRecord
    self.primary_key = 'id'
    validates :id, uniqueness: true
    has_many :program
end
