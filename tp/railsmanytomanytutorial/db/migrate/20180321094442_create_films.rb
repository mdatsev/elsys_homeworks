class CreateFilms < ActiveRecord::Migration[5.1]
  def change
    create_table :films do |t|
      t.integer :cinema_id
      t.string :name

      t.timestamps
    end
  end
end
