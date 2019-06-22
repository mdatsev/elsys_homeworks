class CreateCinemaFilmConnections < ActiveRecord::Migration[5.1]
  def change
    create_table :cinema_film_connections do |t|
      t.string :cinema_id
      t.string :film_id

      t.timestamps
    end
  end
end
