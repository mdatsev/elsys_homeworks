class CreateArticle < ActiveRecord::Migration[5.0]
  def change
    create_table :articles do |t|
    	t.timestamps
    	t.string :title
    	t.text :body
    	t.string :picture
    end
  end
end
