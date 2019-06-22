class CreatePrograms < ActiveRecord::Migration[5.1]
  def change
    create_table :programs do |t|
      t.integer :thread_id

      t.timestamps
    end
  end
end
