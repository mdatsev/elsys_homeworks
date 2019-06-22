class CreateTwos < ActiveRecord::Migration[5.1]
  def change
    create_table :twos do |t|

      t.timestamps
    end
  end
end
