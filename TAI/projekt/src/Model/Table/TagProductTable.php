<?php
namespace App\Model\Table;

use Cake\ORM\Query;
use Cake\ORM\RulesChecker;
use Cake\ORM\Table;
use Cake\Validation\Validator;

/**
 * TagProduct Model
 *
 * @method \App\Model\Entity\TagProduct get($primaryKey, $options = [])
 * @method \App\Model\Entity\TagProduct newEntity($data = null, array $options = [])
 * @method \App\Model\Entity\TagProduct[] newEntities(array $data, array $options = [])
 * @method \App\Model\Entity\TagProduct|bool save(\Cake\Datasource\EntityInterface $entity, $options = [])
 * @method \App\Model\Entity\TagProduct patchEntity(\Cake\Datasource\EntityInterface $entity, array $data, array $options = [])
 * @method \App\Model\Entity\TagProduct[] patchEntities($entities, array $data, array $options = [])
 * @method \App\Model\Entity\TagProduct findOrCreate($search, callable $callback = null, $options = [])
 */
class TagProductTable extends Table
{

    /**
     * Initialize method
     *
     * @param array $config The configuration for the Table.
     * @return void
     */
    public function initialize(array $config)
    {
        parent::initialize($config);

        $this->setTable('tag_product');
        $this->setDisplayField('id');
        $this->setPrimaryKey('id');
    }

    /**
     * Default validation rules.
     *
     * @param \Cake\Validation\Validator $validator Validator instance.
     * @return \Cake\Validation\Validator
     */
    public function validationDefault(Validator $validator)
    {
        $validator
            ->integer('id')
            ->allowEmpty('id', 'create');

        $validator
            ->integer('product')
            ->allowEmpty('product');

        $validator
            ->integer('tag')
            ->allowEmpty('tag');

        return $validator;
    }
}
