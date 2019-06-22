class CreateCinemaFilmConnections < ActiveRecord::Migration[5.1]
  def change
    create_table :cinema_film_connections do |t|
      t.integer :cinema_id
      t.integer :film_id

      t.timestamps
    end
  end
end
