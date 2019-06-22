class CreateFilms < ActiveRecord::Migration[5.1]
  def change
    create_table :films do |t|
      t.string :name
      t.integer :cinema_id

      t.timestamps
    end
  end
end
