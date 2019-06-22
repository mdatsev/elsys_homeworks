class Film < ApplicationRecord
    has_many :cinema_film_connections
    has_many :cinemas, through: :cinema_film_connections

    validates :name, uniqueness: true

    validate :cinema_exists

    def cinema_exists
      errors[:cinema] << "must exist" unless Cinema.exists?(self.cinema_id)
    end  
end
