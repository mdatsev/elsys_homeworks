json.extract! film, :id, :cinema_id, :name, :created_at, :updated_at
json.url film_url(film, format: :json)
