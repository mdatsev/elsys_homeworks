class Cinema < ApplicationRecord
    has_many :cinema_film_connections
    has_many :films, through: :cinema_film_connections
end
