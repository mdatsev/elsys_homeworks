class CreateThreadObjects < ActiveRecord::Migration[5.1]
  def change
    create_table :thread_objects, id: false do |t|
      t.integer :id
      t.integer :value

      t.timestamps
    end
  end
end
