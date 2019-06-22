class CreateRsas < ActiveRecord::Migration[5.1]
  def change
    create_table :rsas do |t|
      t.string :n
      t.string :e
      t.string :d

      t.timestamps
    end
  end
end
