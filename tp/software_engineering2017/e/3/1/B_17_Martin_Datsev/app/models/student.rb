class Student < ApplicationRecord
    belongs_to :school
    validates :second_name, uniqueness: true
end